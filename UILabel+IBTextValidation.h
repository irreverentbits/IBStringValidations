// Copyright (c) 2013-2017 Irreverent Bits
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.


#import <UIKit/UIKit.h>

#import "IBStringValidator.h"


/**
 Allows setting an IBStringValidator onto a UILabel. Once set, the string validator
 state is automatically updated whenever the UILabel text changes. In turn, the
 validBlock and invalidBlock on the string validator will be called when the validity
 of the UILabel text changes.
 */
@interface UILabel (IBTextValidation)

/**
 Accessor for a string validator that has been associated with the UILabel.
 */
- (IBStringValidator*)ibStringValidator;

/**
 Associates a string validator with the UILabel.
 @param stringValidator The string validator to associate with the UILabel.
 */
- (void)ibSetStringValidator:(IBStringValidator*)stringValidator;

@end
